#!/usr/bin/env python

import re
import locale
locale.setlocale( locale.LC_ALL, 'en_US' )

fname = "gost.2009.data"

def generate():
    freq = []
    af = []
    Lu = []
    Tf = []

    with open(fname) as f:
        content = f.read().splitlines()

        for line in content:
            if not line:
                continue

            data = re.split('[ \t]+', line)
            freq.append(data[0])
            af.append(data[1])
            Lu.append(data[2])
            Tf.append(data[3])

    print "// This file is autogenerated. Do not change manually!"
    print "#ifndef ISO226_DATA_H"
    print "#define ISO226_DATA_H\n"

    print "static const int f_size = %d;\n" % (len(freq))

    print "static int f[] = {"
    print "\t",
    print ",\n\t".join(freq)
    print "};\n\n"

    print "static double af[] = {"
    print "\t",
    print ",\n\t".join(af)
    print "};\n\n"

    print "static double Tf[] = {"
    print "\t",
    print ",\n\t".join(Tf)
    print "};\n\n"

    print "static double Lu[] = {"
    print "\t",
    print ",\n\t".join(Lu)
    print "};\n\n"

    print "#endif ISO226_DATA_H\n"



if __name__ == "__main__":
    generate()

