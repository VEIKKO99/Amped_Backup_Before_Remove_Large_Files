namespace papupata {
    namespace licensing {
        static juce::String toBase(const char *rainbow, juce::BigInteger b)
        {
            const juce::BigInteger len((juce::uint32)strlen(rainbow));
            juce::BigInteger remainder;
            juce::String result;

            while (!b.isZero())
            {
                b.divideBy(len, remainder);

                result = rainbow[remainder.getBitRangeAsInt(0, 32)] + result;
            }

            return result;
        }

        juce::String BaseTools::toBase58(const juce::BigInteger &b)
        {
            static const char rainbow[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
            return toBase(rainbow, b);
        }

        static const char rainbow36[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        juce::BigInteger BaseTools::fromBase36(const juce::String &input)
        {
            juce::BigInteger b;
            auto ptr = input.getCharPointer();
            while (!ptr.isEmpty())
            {
                b *= 36;
                if (ptr.isDigit())
                {
                    b += *ptr - '0';
                }
                else if (ptr.isLetter())
                {
                    b += 10 + (ptr.toUpperCase() - 'A');
                }
                ptr++;
            }

            return b;
        }

        juce::String BaseTools::toBase36(const juce::BigInteger &b)
        {
            return toBase(rainbow36, b);
        }
    }
}
