for i in *.txt; do
    echo $i
    ./sampledecomment < $i > output1 2> errors1 && ./decomment < $i > output2 2> errors2 && diff output1 output2 && diff errors1 errors2 && rm -f output1 errors1 output2 errors2
done
