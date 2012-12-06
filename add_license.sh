#!/bin/bash



while [[ -n $1 ]]
do
    tempfile=$(mktemp)
    cat license_header.txt $1 > $tempfile
    echo $tempfile
    mv $tempfile $1
    shift
done


