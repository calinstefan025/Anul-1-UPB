#!/bin/bash

TESTS_NO_PROBLEMS=(15 16)
PROBLEMS_NO=2
TOTAL=0
WORKING_DIR=`pwd`
array_points=(0 0 0)
max_array_points=(0 60 65)
make

function check_test_1() {
	in_path=$1
	out_path=$2
	ref_path=$3
	test_no=$4
	problem_no=$5
	exec=bingo


	if test $4 -le 9; then 
		echo -n "Test:  $test_no ...................... "
	else echo -n "Test: $test_no ...................... "
	fi

	./$exec < $in_path > $out_path

	# Check the result
	diff $ref_path $out_path 2>&1 1> my_diff

	if test $? -eq 0; then
		echo "PASS"
		array_points[$problem_no]=$(echo "scale=4; ${array_points[$problem_no]} + 4" | bc)
	else
		echo "FAILED"
	fi
}

function check_test_2() {
	in_path=$1
	out_path=$2
	ref_path=$3
	test_no=$4
	problem_no=$5
	exec=biblioteca


	if test $4 -le 9; then 
		echo -n "Test:  $test_no ...................... "
	else echo -n "Test: $test_no ...................... "
	fi

	./$exec < $in_path > $out_path

	# Check the result
	diff $ref_path $out_path 2>&1 1> my_diff

	if test $? -eq 0; then
		echo "PASS"
		array_points[$problem_no]=$(echo "scale=4; ${array_points[$problem_no]} + 4.0625" | bc)
	else
		echo "FAILED"
	fi
}

function run_tests_for_problem_1() {
	PROBLEM_NO=$1
	NO_TESTS=${TESTS_NO_PROBLEMS[$((PROBLEM_NO-1))]}
		
	if test ! -x "bingo"; then
		echo "Executable for problem $1 is missing"
		return 1
	fi

	input="$WORKING_DIR/tests/bingo/in"
	ref="$WORKING_DIR/tests/bingo/ref"
	output="$WORKING_DIR/tests/bingo/out"

	if [ ! -d "$output" ]; then
		mkdir $output
	fi

	echo "===== Running tests for problem $PROBLEM_NO ======="
	for ((i=0;i<$NO_TESTS;i++)); do
		test_input="$input/"$i"-bingo.in"
		test_output="$output/"$i"-bingo.out"
		test_ref="$ref/"$i"-bingo.ref"
		check_test_1 $test_input $test_output $test_ref $i $PROBLEM_NO
	done
	echo "====== You got ${array_points[$PROBLEM_NO]} out of ${max_array_points[$PROBLEM_NO]} for $PROBLEM_NO ======="

	echo ""
}

function run_tests_for_problem_2() {
	PROBLEM_NO=$1
	NO_TESTS=${TESTS_NO_PROBLEMS[$((PROBLEM_NO-1))]}
		
	if test ! -x "biblioteca"; then
		echo "Executable for problem $1 is missing"
		return 1
	fi

	input="$WORKING_DIR/tests/biblioteca/in"
	ref="$WORKING_DIR/tests/biblioteca/ref"
	output="$WORKING_DIR/tests/biblioteca/out"

	if [ ! -d "$output" ]; then
		mkdir $output
	fi

	echo "===== Running tests for problem $PROBLEM_NO ======="
	for ((i=0;i<$NO_TESTS;i++)); do
		test_input="$input/"$i"-biblioteca.in"
		test_output="$output/"$i"-biblioteca.out"
		test_ref="$ref/"$i"-biblioteca.ref"
		check_test_2 $test_input $test_output $test_ref $i $PROBLEM_NO
	done
	echo "====== You got ${array_points[$PROBLEM_NO]} out of ${max_array_points[$PROBLEM_NO]} for $PROBLEM_NO ======="

	echo ""
}

function run_tests() {
	run_tests_for_problem_1 1
	run_tests_for_problem_2 2

}

if [ $# -eq 0 ]; then
	run_tests
else 
	if [ "$1" -gt "2" ] || [ "$1" -lt "1" ]; then
		echo "Invalid problem number"
		exit 1
	fi

	run_tests_for_problem $1
fi

# And the result is ...

for ((k=1;k<=2;k++)); do
	TOTAL=$(echo "scale=4; ${array_points[$k]} + $TOTAL" | bc)
done

echo "TOTAL: $TOTAL/125"
echo ""
make clean
rm my_diff