const state = {
    stackA: [],
    stackB: [],
    instructions: [],
    currentStep: -1,
    animating: false,
    animTimer: null,
    animationSpeed: 2.5,
    solving: false,
    allNumbers: []
};

function init() {
    setupEventListeners();
    renderStacks();
}

function setupEventListeners() {
    document.getElementById('random-btn').addEventListener('click', () => generateRandom(100));
    document.getElementById('random500-btn').addEventListener('click', () => generateRandom(500));
    document.getElementById('load-btn').addEventListener('click', loadNumbers);
    document.getElementById('solve-btn').addEventListener('click', handleSolveClick);
    document.getElementById('speed-slider').addEventListener('input', handleSpeedChange);
}

function handleSpeedChange(e) {
    const normalized = (200 - parseInt(e.target.value)) / 200;
    state.animationSpeed = Math.pow(normalized, 3) * 20;
}

function generateRandom(count) {
    fetch('/api/random', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ count: count })
    })
    .then(res => res.json())
    .then(data => {
        document.getElementById('numbers-input').value = data.numbers.join(' ');
        loadNumbers();
    })
    .catch(err => setStatus('Error generating random numbers', 'error'));
}

function loadNumbers() {
    const input = document.getElementById('numbers-input').value.trim();
    if (!input) {
        setStatus('Enter some numbers first', 'error');
        return;
    }

    const numbers = input.split(/\s+/).map(n => parseInt(n));
    
    if (numbers.some(isNaN)) {
        setStatus('Invalid numbers', 'error');
        return;
    }

    state.stackA = numbers;
    state.stackB = [];
    state.instructions = [];
    state.currentStep = -1;
    state.allNumbers = [...numbers].sort((a, b) => a - b);
    renderStacks();
    renderMoves();
    updateStats();
    setStatus(`Loaded ${numbers.length} numbers`, 'success');
}

async function handleSolveClick() {
    if (state.animating) {
        cancelAnimation();
        return;
    }

    if (state.stackA.length === 0) {
        setStatus('Load numbers first', 'error');
        return;
    }

    if (state.instructions.length > 0 && state.currentStep === state.instructions.length - 1) {
        resetToStart();
        return;
    }

    await solve();
}

function resetToStart() {
    state.currentStep = -1;
    loadNumbers();
    setSolveButtonMode('solve');
}

async function solve() {
    if (state.solving) return;

    state.solving = true;
    disableControls(true);
    setStatus('Solving...');

    try {
        const res = await fetch('/api/solve', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ numbers: state.stackA })
        });

        const data = await res.json();

        if (data.error) {
            setStatus(data.error, 'error');
            state.solving = false;
            disableControls(false);
            return;
        }

        state.instructions = data.instructions;
        state.currentStep = -1;
        
        setStatus(`Solved in ${data.count} moves`, 'success');
        state.solving = false;
        disableControls(false);
        
        renderMoves();
        updateStats();
        startAnimation();
    } catch (err) {
        setStatus('Error: ' + err.message, 'error');
        state.solving = false;
        disableControls(false);
    }
}

function startAnimation() {
    state.animating = true;
    setSolveButtonMode('cancel');
    animateStep();
}

function cancelAnimation() {
    if (state.animTimer) {
        clearTimeout(state.animTimer);
        state.animTimer = null;
    }
    state.animating = false;
    setSolveButtonMode('solve');
    setStatus('Animation cancelled', 'error');
}

function animateStep() {
    if (state.currentStep >= state.instructions.length - 1) {
        state.animating = false;
        setSolveButtonMode('solve');
        setStatus('Solved!', 'success');
        return;
    }

    if (state.animationSpeed === 0) {
        while (state.currentStep < state.instructions.length - 1) {
            state.currentStep++;
            executeInstruction(state.instructions[state.currentStep]);
        }
        renderStacks();
        renderMoves();
        updateStats();
        state.animating = false;
        setSolveButtonMode('solve');
        setStatus('Solved!', 'success');
        return;
    }

    const batchSize = state.animationSpeed < 16 ? Math.ceil(48 / state.animationSpeed) : 1;

    for (let i = 0; i < batchSize && state.currentStep < state.instructions.length - 1; i++) {
        state.currentStep++;
        executeInstruction(state.instructions[state.currentStep]);
    }

    renderStacks();
    renderMoves();
    updateStats();

    state.animTimer = setTimeout(animateStep, state.animationSpeed);
}

function executeInstruction(instruction) {
    switch (instruction) {
        case 'sa': swap(state.stackA); break;
        case 'sb': swap(state.stackB); break;
        case 'ss': swap(state.stackA); swap(state.stackB); break;
        case 'ra': rotate(state.stackA); break;
        case 'rb': rotate(state.stackB); break;
        case 'rr': rotate(state.stackA); rotate(state.stackB); break;
        case 'rra': reverseRotate(state.stackA); break;
        case 'rrb': reverseRotate(state.stackB); break;
        case 'rrr': reverseRotate(state.stackA); reverseRotate(state.stackB); break;
        case 'pa': push(state.stackB, state.stackA); break;
        case 'pb': push(state.stackA, state.stackB); break;
    }
}

function swap(stack) {
    if (stack.length >= 2) {
        [stack[0], stack[1]] = [stack[1], stack[0]];
    }
}

function rotate(stack) {
    if (stack.length >= 2) {
        stack.push(stack.shift());
    }
}

function reverseRotate(stack) {
    if (stack.length >= 2) {
        stack.unshift(stack.pop());
    }
}

function push(from, to) {
    if (from.length > 0) {
        to.unshift(from.shift());
    }
}

function getRank(val) {
    return state.allNumbers.indexOf(val);
}

function renderStacks() {
    const stackAEl = document.getElementById('stack-a');
    const stackBEl = document.getElementById('stack-b');
    const total = state.allNumbers.length || 1;
    const maxItems = Math.max(state.stackA.length, state.stackB.length, 1);
    const barHeight = Math.max(1, Math.min(8, Math.floor(400 / maxItems)));

    stackAEl.innerHTML = state.stackA.map((val, i) => {
        const rank = getRank(val);
        const pct = ((rank + 1) / total) * 100;
        const hl = i === 0 && state.animating ? ' highlight' : '';
        return `<div class="stack-item${hl}" style="height:${barHeight}px"><div class="bar bar-a" style="width:${pct}%"></div></div>`;
    }).join('');

    stackBEl.innerHTML = state.stackB.map((val, i) => {
        const rank = getRank(val);
        const pct = ((rank + 1) / total) * 100;
        const hl = i === 0 && state.animating ? ' highlight' : '';
        return `<div class="stack-item${hl}" style="height:${barHeight}px"><div class="bar bar-b" style="width:${pct}%"></div></div>`;
    }).join('');
}

function renderMoves() {
    const container = document.getElementById('moves-content');
    
    container.innerHTML = state.instructions.map((inst, i) => {
        let cls = 'move-item';
        if (i < state.currentStep) cls += ' done';
        if (i === state.currentStep) cls += ' current';
        return `<div class="${cls}">${inst}</div>`;
    }).join('');

    if (state.currentStep >= 0) {
        const current = container.children[state.currentStep];
        if (current) {
            current.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
        }
    }
}

function updateStats() {
    document.getElementById('stat-moves').textContent = state.instructions.length;
    document.getElementById('stat-step').textContent = 
        `${Math.max(0, state.currentStep + 1)}/${state.instructions.length}`;
}

function setSolveButtonMode(mode) {
    const btn = document.getElementById('solve-btn');
    if (mode === 'cancel') {
        btn.textContent = 'Cancel';
        btn.className = 'btn btn-secondary';
    } else {
        btn.textContent = 'Solve';
        btn.className = 'btn btn-accent';
    }
}

function disableControls(disabled) {
    document.getElementById('random-btn').disabled = disabled;
    document.getElementById('load-btn').disabled = disabled;
}

let statusTimeout = null;

function setStatus(msg, type = '') {
    const el = document.getElementById('status-msg');
    
    if (statusTimeout) {
        clearTimeout(statusTimeout);
        statusTimeout = null;
    }
    
    el.textContent = msg;
    el.className = 'status-msg' + (type ? ' ' + type : '') + (msg ? ' visible' : '');
    
    if (msg) {
        statusTimeout = setTimeout(() => {
            el.classList.remove('visible');
            statusTimeout = null;
        }, 4000);
    }
}

document.addEventListener('DOMContentLoaded', init);
