#!/bin/sh

KEYBITS=512

workdir=$(mktemp -d privkey.XXXXXX)
echo Using $workdir
pushd $workdir
openssl genrsa -f4 -out privkey.pem $KEYBITS
openssl pkey -in privkey.pem -text -out privkey.txt
cat privkey.txt | sed -n -e '/modulus:/,/publicExponent:/p' | egrep -v 'modulus:|public' | tr -d ':\n\r ' > modulus.txt
cat privkey.txt | sed -n -e '/privateExponent:/,/prime1:/p' | egrep -v 'private|prime1' | tr -d ':\n\r ' > privexp.txt

cat <<EOF > Keys.cpp
#include "JuceHeader.h"
// Automagically generated with papupatakeytools/create_keys.sh

const unsigned char papupata::licensing::License::exponent[3]{
    0x01 ^ 0xca,
    0x00 ^ 0xfe,
    0x01 ^ 0xba

};
const unsigned char papupata::licensing::License::modulus[65]{
EOF

cat modulus.txt | perl -ne '@suffixes = qw(0xca 0xfe 0xba 0xbe); $index=0; @arr = unpack("(A2)*", $_); map { print "    0x".$_." ^ ".$suffixes[$index].",\n"; $index = ($index + 1) % 4;} @arr;' >> Keys.cpp

cat <<EOF >> Keys.cpp
};

juce::RSAKey authPrivateKey(juce::String(
    "
EOF

perl -pi -e 'chomp if eof' Keys.cpp
cat privexp.txt >> Keys.cpp
   
cat <<EOF >> Keys.cpp
"
    ","
    "
EOF

perl -pi -e 'chomp if eof' Keys.cpp
cat modulus.txt >> Keys.cpp

cat <<EOF >> Keys.cpp
"));
EOF

#cat Keys.cpp

popd $workdir

#rm -rf "$workdir"
