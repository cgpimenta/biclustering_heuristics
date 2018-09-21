#!/usr/bin/env python

import pandas as pd
import sys

from random import uniform

input_filename = sys.argv[1]
output_filename = sys.argv[2]

df = pd.read_csv(input_filename)

df = df.select_dtypes(include=['number'])

max_val = df.max().max()
min_val = df.min().min()

df = df.fillna(uniform(2 * min_val, 2 * max_val))

df.to_csv(output_filename, index=False, header=None)
