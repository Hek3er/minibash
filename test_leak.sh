#!/bin/bash

# Run leaks in a loop
while true; do
    leaks "minishell"
    sleep 1  # Adjust sleep duration as needed
done

