#!/usr/bin/env python

import pandas as pd
import numpy as np
import sys

from random import uniform

input_filename = sys.argv[1]
output_filename = sys.argv[2]

def get_variance(df):
    matrix = df.values.tolist()
    num_rows = df.shape[0]
    num_cols = df.shape[1]

    mean = get_mean(df)

    total = 0

    for row in range(num_rows):
        for col in range(num_cols):
            dev = matrix[row][col] - mean
            total += dev * dev

    return total / (num_rows * num_cols)


def get_mean(df):
    matrix = df.values.tolist()
    num_rows = df.shape[0]
    num_cols = df.shape[1]

    total = np.sum(matrix)

    return total / (num_rows * num_cols)


df = pd.read_csv(input_filename, header=None)

df = df.select_dtypes(include=['number'])

max_val = df.max().max()
min_val = df.min().min()
mean_val = df.mean().mean()
variance = get_variance(df)

print('min:\t', min_val)
print('max:\t', max_val)
print('mean:\t', mean_val)
print('shape:\t', df.shape)
print('var:\t', variance)

df = df.fillna(uniform(2 * min_val, 2 * max_val))

df.to_csv(output_filename, index=False, header=None)
