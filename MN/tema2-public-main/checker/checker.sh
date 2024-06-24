#!/bin/bash

setup()
{
	# Make sure we don't get scammed
	rm -rf ../src/checker
	cp -r ../src/. .
}

run()
{
	python3 ./checker.py | tee checker.out

	final_score=$(grep "FINAL SCORE" checker.out);

	if [ -z "$final_score" ]; then
		grade=0;
	else
		grade=$(echo $final_score | cut -d' ' -f3 | cut -d'.' -f1 | cut -d'p' -f1);
	fi

	echo "Total: $grade/100";
}

setup
run
