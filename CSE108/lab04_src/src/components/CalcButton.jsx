import { Button } from '@mui/material';
import './Calculator.css';

// This component demonstrates PROPS (Requirement 4)
function CalcButton({ label, onClick, variant, span, isActive }) {
  let className = `calc-btn ${variant}`;
  if (isActive) className += ' active';
  if (span) className += ` span-${span}`;

  return (
    <Button
      className={className}
      onClick={onClick}
      variant="contained"
      disableElevation
    >
      {label}
    </Button>
  );
}

export default CalcButton;