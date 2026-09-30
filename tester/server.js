const express = require('express');
const { execSync } = require('child_process');
const path = require('path');
const fs = require('fs');

const app = express();
const PORT = 3000;

app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

const PUSH_SWAP = path.resolve(__dirname, '..', 'push_swap');

function ensureBinary() {
    if (!fs.existsSync(PUSH_SWAP)) {
        throw new Error('push_swap binary not found. Run "make" first.');
    }
}

app.post('/api/solve', (req, res) => {
    try {
        ensureBinary();
        const numbers = req.body.numbers;

        if (!Array.isArray(numbers) || numbers.length === 0) {
            return res.status(400).json({ error: 'Numbers array is required' });
        }

        const args = numbers.join(' ');
        const output = execSync(`"${PUSH_SWAP}" ${args}`, {
            timeout: 30000,
            encoding: 'utf8',
            maxBuffer: 10 * 1024 * 1024
        });

        const instructions = output.trim().split('\n').filter(i => i.length > 0);

        res.json({
            instructions,
            count: instructions.length,
            numbers
        });
    } catch (err) {
        if (err.status === 1) {
            return res.status(400).json({ error: 'Invalid input (duplicates, non-numbers, or out of range)' });
        }
        res.status(500).json({ error: err.message });
    }
});

app.post('/api/random', (req, res) => {
    const count = req.body.count || 100;
    const numbers = new Set();

    while (numbers.size < count) {
        numbers.add(Math.floor(Math.random() * 10000) - 5000);
    }

    res.json({ numbers: Array.from(numbers) });
});

app.listen(PORT, '0.0.0.0', () => {
    console.log(`Push Swap Tester running at http://localhost:${PORT}`);
    console.log(`Access from Windows at http://$(hostname -I | awk '{print $1}'):${PORT}`);
});
