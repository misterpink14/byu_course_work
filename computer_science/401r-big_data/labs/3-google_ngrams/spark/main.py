from __future__ import print_function
import sys
import heapq
from pyspark import SparkContext


def interestingWords(lines):
    '''What interesting words have effectively disappeared from the English
        language and when did they last get used?
    '''
    words = lines.map(
        lambda x: (x.split()[:2])
    ).combineByKey(
        unicode,
        lambda x, value: (x if isinstance(x, list) else [x]) + [value],
        lambda x, y: (
            x if isinstance(x, list) else [x]) + (
            y if isinstance(y, list) else [y])
    ).filter(
        lambda x: '2008' not in x[1]
    ).filter(
        lambda x: '2007' not in x[1]
    ).filter(
        lambda x: '2006' not in x[1]
    ).filter(
        lambda x: '2005' not in x[1]
    ).map(
        lambda x: (x[0], max(x[1]))
    ).sortBy(
        lambda x: x[1]
    ).map(
        lambda x: ''.join([
            "Word: ",
            x[0],
            ", Year last used: ",
            x[1]
        ]))
    words.saveAsTextFile(sys.argv[2])


def topWords(lines):
    '''What were the top-10 trending topics (i.e. most used phrases of 4 words)
        for each decade you have been alive?
    '''
    def splitIt(x):
        X = x.split()
        return (X[1][:3], (X[2], X[0]))

    def top10(x, y):
        if not isinstance(x, list):
            x = [x]
        if not isinstance(y, list):
            y = [y]
        if len(x) + len(y) <= 10:
            return x + y
        return list(heapq.nlargest(10, x + y))

    words = lines.map(
        splitIt
    ).filter(
        lambda x: int(x[0]) > 197
    ).combineByKey(
        lambda x: x,
        top10,
        top10
    ).sortBy(
        lambda x: x[0]
    )
    words.saveAsTextFile(sys.argv[3])


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: main <input> <output1> <output2>", file=sys.stderr)
        exit(-1)
    sc = SparkContext(appName="NGrams")
    lines = sc.textFile(sys.argv[1])
    # interestingWords(lines)
    topWords(lines)
