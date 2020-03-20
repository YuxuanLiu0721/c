#!/bin/bash
cat $2|tr "`sed -n 1p $1`" 'a-z'|tr "`sed -n 2p $1`" 'A-Z'
