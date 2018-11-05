#!/usr/bin/env python

import pandas as pd
import sys
import re

data_file = sys.argv[1]

df = pd.read_csv(data_file, header=None)
mean = df.mean(axis=1).mean(axis=0)

df = df.applymap(lambda x: 0 if x < mean else 1)

dataset_name = re.sub('\.csv', '', data_file)
df.to_csv(dataset_name + '_binary.csv', header=False, index=False)
