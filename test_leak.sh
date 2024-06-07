#!/bin/bash

# Function to find the PID of a process by name
get_pid() {
    local process_name="$1"
    local pid=$(pgrep -o "$process_name")
    echo "$pid"
}

# Run leaks in a loop for the minishell process
while true; do
    pid=$(get_pid "minishell")
    if [ -n "$pid" ]; then
        echo "Running leaks for minishell (PID: $pid)"
        leaks "$pid"
    else
        echo "minishell process not found."
    fi
    sleep 1  # Adjust sleep duration as needed
done