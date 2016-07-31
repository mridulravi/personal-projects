#!/bin/bash
awk -v CONVFMT=%.6g '
function convert(t) {

    split(t,Arr,":")
    return Arr[1]*3600+Arr[2]*60+Arr[3]

    }
{printf "%0.3f %s\n",convert($1), $2 }
' log.txt
