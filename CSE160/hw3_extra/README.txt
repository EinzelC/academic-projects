Requirements: Python 3.6 or newer. No third-party packages.

Compile/check (optional, Python is interpreted):
    python3 -m py_compile fetch.py

Run:
    python3 fetch.py

The program prints the raw HTTP response (status line, headers, body)
received from www.ucmerced.edu on port 80.