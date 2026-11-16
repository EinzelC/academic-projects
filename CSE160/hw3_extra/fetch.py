#!/usr/bin/env python3
"""Send a raw HTTP/1.1 GET request to www.ucmerced.edu:80 and print the reply."""

import socket
import sys

HOST = "www.ucmerced.edu"
PORT = 80

# Build the request as specified by assignment. \r is 0x0D and \n is 0x0A.
REQUEST = (
    "GET / HTTP/1.1\r\n"
    "Host: www.ucmerced.edu:80\r\n"
    "Connection: close\r\n"
    "\r\n"
).encode("ascii")


def fetch(host: str, port: int, request: bytes) -> bytes:
    """Open a TCP connection, send the request, and return all bytes received."""
    chunks = []
    # create_connection resolves the name and opens the TCP connection.
    with socket.create_connection((host, port), timeout=10) as sock:
        sock.sendall(request)
        # The server closes the connection after responding (Connection: close),
        # so recv() returns b"" when the response is complete.
        while True:
            data = sock.recv(4096)
            if not data:
                break
            chunks.append(data)
    return b"".join(chunks)


def main() -> int:
    try:
        response = fetch(HOST, PORT, REQUEST)
    except OSError as exc:
        print(f"Error: could not fetch from {HOST}:{PORT}: {exc}", file=sys.stderr)
        return 1

    # Write the raw bytes so headers and body print exactly as received.
    sys.stdout.buffer.write(response)
    sys.stdout.buffer.flush()
    return 0


if __name__ == "__main__":
    sys.exit(main())