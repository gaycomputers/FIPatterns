#!/bin/bash
#usage scipt.sh name
NAME=$1
FIAASCO_HOME="$PWD/.."
echo $FIAASCO_HOME
SOURCE_HOME="$FIAASCO_HOME/fi-source/fi-test"
SOURCE="$SOURCE_HOME/src/fi-test.c"
RESULTS_HOME="$FIAASCO_HOME/cm_Results"
mkdir $RESULTS_HOME/$NAME
RESULTS="$RESULTS_HOME/$NAME"
BINARY="$FIAASCO_HOME/fi-source/fi-test/bin/fi-test.bin"
ELF="$FIAASCO_HOME/fi-source/fi-test/bin/fi-test.elf"
FISIM="$FIAASCO_HOME/fiaascoapp/fisim.sh"
ANALYZE="$FIAASCO_HOME/fi-source/analyze.sh"
RESULT_RAW="$RESULTS/${NAME}_raw.txt"
RESULT_ANALYZED="$RESULTS/${NAME}_analyzed.txt"
RESULT_MAKE="$RESULTS/${NAME}_make.txt"
echo $RESULTS
echo $BINARY
echo $FISIM
echo $RESULT_RAW
echo $ANALYZE

cd $SOURCE_HOME
make | tee $RESULT_MAKE
cd $FIAASCO_HOME
cat $BINARY | $FISIM | tee $RESULT_RAW
PID=$!
wait $PID
$ANALYZE $RESULT_RAW $ELF details | tee $RESULT_ANALYZED && cp $BINARY $RESULTS/${NAME}.bin && cp $ELF $RESULTS/${NAME}.elf && cp $SOURCE $RESULTS/${NAME}.c