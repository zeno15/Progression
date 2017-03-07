#!/bin/bash


set -ev

if [[ "$OSTYPE" == "linux-gnu" ]]; then
        # ...
		echo Linux
elif [[ "$OSTYPE" == "darwin"* ]]; then
        # Mac OSX
		echo Mac OSX
fi