#!/bin/bash
cat $2|tr 'a-z' "`sed -n 1p $1`"|tr 'A-Z' "`sed -n 2p $1`"
