#!/bin/env bash

dd if=/dev/zero of=test06_100meg_file bs=100M count=1
dd if=/dev/zero of=test07_1gig_file bs=1G count=1