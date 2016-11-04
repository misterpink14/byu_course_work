from __future__ import print_function
import sys
from operator import add
from pyspark import SparkContext


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: netflix <input> <output>", file=sys.stderr)
        exit(-1)
    sc = SparkContext(appName="Netflix")
    lines = sc.textFile(sys.argv[1], 1)
    ratings = dict(lines.map(lambda x: (x.split()[1] + ":" + x.split()[2], x.split()[0])) \
        .filter(lambda x: x[1] == "1488844") \
        .collect())
    people = lines.map(lambda x: (x.split()[0], x.split()[1] + ":" + x.split()[2])) \
        .filter(lambda x: x[0] != "1488844" and x[1] in ratings) \
        .map(lambda x: (x[0],1)) \
        .reduceByKey(add).sortBy(lambda x: (-x[1], x[0]))
    people.saveAsTextFile(sys.argv[2])
    sc.stop()
