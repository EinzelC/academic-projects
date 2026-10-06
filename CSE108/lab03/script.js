// Grab elements from the DOM
const display = document.getElementById('display');
const numbers = document.querySelectorAll('.number');
const operators = document.querySelectorAll('.operator');
const equalsBtn = document.getElementById('equals-btn');
const clearBtn = document.querySelector('.clear');
const decimalBtn = document.querySelector('.decimal');

// State variables
let currentInput = '0';
let previousInput = '';
let activeOperator = null;
let shouldResetScreen = false;
let lastOperator = null; // For repeated equals
let lastOperand = null;  // For repeated equals

// Update the display field
function updateDisplay() {
    display.textContent = currentInput;
}

// 1 & 2. Number Button Logic
numbers.forEach(num => {
    num.addEventListener('click', () => {
        if (shouldResetScreen) {
            currentInput = '';
            shouldResetScreen = false;
            // Remove highlight from operators when a new number is input
            operators.forEach(op => op.classList.remove('active')); 
        }
        
        // Prevent multiple leading zeros
        if (currentInput === '0' && num.dataset.value !== '0') {
            currentInput = num.dataset.value;
        } else if (currentInput === '0' && num.dataset.value === '0') {
            return; 
        } else {
            currentInput += num.dataset.value;
        }
        updateDisplay();
    });
});

// 3. Decimal Button Logic (Only one decimal allowed per number)
decimalBtn.addEventListener('click', () => {
    if (shouldResetScreen) {
        currentInput = '0.';
        shouldResetScreen = false;
        operators.forEach(op => op.classList.remove('active'));
        updateDisplay();
        return;
    }
    if (!currentInput.includes('.')) {
        currentInput += '.';
        updateDisplay();
    }
});

// 2 & 4. Operator Logic (Highlighting & Chaining)
operators.forEach(op => {
    op.addEventListener('click', () => {
        // Req 4: If a number was already input, act as equals to chain calculations
        if (!shouldResetScreen && activeOperator && previousInput !== '') {
            calculate();
        } else {
            previousInput = currentInput;
        }

        activeOperator = op.dataset.value;
        shouldResetScreen = true;

        // Req 2: Highlight the active operator
        operators.forEach(o => o.classList.remove('active'));
        op.classList.add('active');
    });
});

// 3 & 5. Equals Button Logic (Includes Repeated Equals)
equalsBtn.addEventListener('click', () => {
    if (activeOperator && shouldResetScreen && lastOperator) {
        // Req 3: Repeated equals (e.g., 2+4=6, then =10, then =14)
        previousInput = currentInput;
        currentInput = lastOperand;
        activeOperator = lastOperator;
        calculate();
    } else if (activeOperator && previousInput !== '') {
        // Normal calculation
        lastOperator = activeOperator;
        lastOperand = currentInput;
        calculate();
    }
    
    shouldResetScreen = true;
    operators.forEach(op => op.classList.remove('active')); // Remove highlight
});

// 6. Clear Button Logic
clearBtn.addEventListener('click', () => {
    currentInput = '0';
    previousInput = '';
    activeOperator = null;
    shouldResetScreen = false;
    lastOperator = null;
    lastOperand = null;
    operators.forEach(op => op.classList.remove('active'));
    updateDisplay();
});

// Core Calculation Function
function calculate() {
    const prev = parseFloat(previousInput);
    const curr = parseFloat(currentInput);
    if (isNaN(prev) || isNaN(curr)) return;

    let result = 0;
    switch (activeOperator) {
        case '+': result = prev + curr; break;
        case '-': result = prev - curr; break;
        case '*': result = prev * curr; break;
        case '/': 
            if (curr === 0) {
                currentInput = 'Error';
                updateDisplay();
                return;
            }
            result = prev / curr; 
            break;
        default: return;
    }

    // Fix floating point math issues (like 0.1 + 0.2 = 0.300000004)
    currentInput = (Math.round(result * 100000000) / 100000000).toString();
    previousInput = currentInput; 
    updateDisplay();
}