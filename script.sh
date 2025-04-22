#!/bin/bash

# Usage: ./run_client.sh <address> <port> <filename> <N>

if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <address> <port> <filename> <N>"
    exit 1
fi

ADDRESS=$1
PORT=$2
FILENAME=$3
N=$4

# Extract base name and extension
BASENAME=$(basename "$FILENAME")
NAME="${BASENAME%.*}"
EXT="${BASENAME##*.}"

# Timeout duration in seconds
TIMEOUT_DURATION=10

# Loop from 1 to N
for ((i=1; i<=N; i++)); do
    OUTPUT="${NAME}${i}.${EXT}"
    echo "[`date +%H:%M:%S`] Launching: $OUTPUT"

    # Run with timeout in background and silence output
    timeout "${TIMEOUT_DURATION}"s python3 client.py "$ADDRESS" "$PORT" "$OUTPUT" > /dev/null 2>&1 &
done

echo "[`date +%H:%M:%S`] Waiting for all background processes..."
wait
echo "[`date +%H:%M:%S`] All done!"
