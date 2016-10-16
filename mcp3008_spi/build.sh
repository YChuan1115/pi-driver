#!/bin/sh

gcc -I./ bcm2835.c mcp3008.c main.c -o test
