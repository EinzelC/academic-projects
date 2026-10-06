import { useState } from 'react';
import { TextField, Box } from '@mui/material';
import CalcButton from './CalcButton';
import './Calculator.css';

function Calculator() {
  // useState Hooks (Requirement 4)
  const [currentInput, setCurrentInput] = useState('0');
  const [previousInput, setPreviousInput] = useState('');
  const [activeOperator, setActiveOperator] = useState(null);
  const [shouldResetScreen, setShouldResetScreen] = useState(false);
  const [lastOperator, setLastOperator] = useState(null);
  const [lastOperand, setLastOperand] = useState(null);
  const [highlightedOp, setHighlightedOp] = useState(null);

  // Core Calculation Function (from Lab 3 script.js)
  const calculate = (op, prev, curr) => {
    const p = parseFloat(prev);
    const c = parseFloat(curr);
    if (isNaN(p) || isNaN(c)) return curr;

    let result = 0;
    switch (op) {
      case '+': result = p + c; break;
      case '-': result = p - c; break;
      case '*': result = p * c; break;
      case '/': 
        if (c === 0) return 'Error';
        result = p / c; 
        break;
      default: return curr;
    }
    return (Math.round(result * 100000000) / 100000000).toString();
  };

  const handleNumber = (value) => {
    if (currentInput === 'Error') {
      setCurrentInput(value);
      setShouldResetScreen(false);
      setHighlightedOp(null);
      return;
    }
    if (shouldResetScreen) {
      setCurrentInput(value);
      setShouldResetScreen(false);
      setHighlightedOp(null);
    } else {
      if (currentInput === '0' && value !== '0') {
        setCurrentInput(value);
      } else if (currentInput === '0' && value === '0') {
        return; 
      } else {
        setCurrentInput(prev => prev + value);
      }
    }
  };

  const handleDecimal = () => {
    if (currentInput === 'Error') {
      setCurrentInput('0.');
      setShouldResetScreen(false);
      setHighlightedOp(null);
      return;
    }
    if (shouldResetScreen) {
      setCurrentInput('0.');
      setShouldResetScreen(false);
      setHighlightedOp(null);
      return;
    }
    if (!currentInput.includes('.')) {
      setCurrentInput(prev => prev + '.');
    }
  };

  const handleOperator = (op) => {
    if (currentInput === 'Error') return;

    if (!shouldResetScreen && activeOperator && previousInput !== '') {
      const result = calculate(activeOperator, previousInput, currentInput);
      setPreviousInput(result);
      setCurrentInput(result);
    } else {
      setPreviousInput(currentInput);
    }
    setActiveOperator(op);
    setShouldResetScreen(true);
    setHighlightedOp(op);
  };

  const handleEquals = () => {
    if (currentInput === 'Error') return;

    if (activeOperator && shouldResetScreen && lastOperator) {
      const result = calculate(lastOperator, currentInput, lastOperand);
      setCurrentInput(result);
      setPreviousInput(result);
      setShouldResetScreen(true);
    } else if (activeOperator && previousInput !== '') {
      setLastOperator(activeOperator);
      setLastOperand(currentInput);
      const result = calculate(activeOperator, previousInput, currentInput);
      setCurrentInput(result);
      setPreviousInput(result);
      setShouldResetScreen(true);
    }
    setHighlightedOp(null);
  };

  const handleClear = () => {
    setCurrentInput('0');
    setPreviousInput('');
    setActiveOperator(null);
    setShouldResetScreen(false);
    setLastOperator(null);
    setLastOperand(null);
    setHighlightedOp(null);
  };

  return (
    <Box className="calculator">
      {/* Material UI TextField (Requirement 3) */}
      <TextField
        className="display"
        value={currentInput}
        InputProps={{ readOnly: true }}
        variant="outlined"
      />

      <div className="calc-grid">
        <CalcButton label="7" variant="number" onClick={() => handleNumber('7')} />
        <CalcButton label="8" variant="number" onClick={() => handleNumber('8')} />
        <CalcButton label="9" variant="number" onClick={() => handleNumber('9')} />
        <CalcButton label="/" variant="operator" onClick={() => handleOperator('/')} isActive={highlightedOp === '/'} />

        <CalcButton label="4" variant="number" onClick={() => handleNumber('4')} />
        <CalcButton label="5" variant="number" onClick={() => handleNumber('5')} />
        <CalcButton label="6" variant="number" onClick={() => handleNumber('6')} />
        <CalcButton label="*" variant="operator" onClick={() => handleOperator('*')} isActive={highlightedOp === '*'} />

        <CalcButton label="1" variant="number" onClick={() => handleNumber('1')} />
        <CalcButton label="2" variant="number" onClick={() => handleNumber('2')} />
        <CalcButton label="3" variant="number" onClick={() => handleNumber('3')} />
        <CalcButton label="-" variant="operator" onClick={() => handleOperator('-')} isActive={highlightedOp === '-'} />

        <CalcButton label="0" variant="number" span={2} onClick={() => handleNumber('0')} />
        <CalcButton label="." variant="decimal" onClick={handleDecimal} />
        <CalcButton label="+" variant="operator" onClick={() => handleOperator('+')} isActive={highlightedOp === '+'} />

        <CalcButton label="C" variant="clear" onClick={handleClear} />
        <CalcButton label="=" variant="equals" span={3} onClick={handleEquals} />
      </div>
    </Box>
  );
}

export default Calculator;