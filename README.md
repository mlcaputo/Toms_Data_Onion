# Tom's Data Onion
Decoding Tom's Data Onion using C++  
https://www.tomdalling.com/toms-data-onion/

## Layer 0: ASCII85
ASCII85 is a binary-to-text encoding. These encodings are
useful when you need to send arbitrary binary data as text,
such as sending an image as an email attachment, or
embedding obfuscated data in a text file. It takes four
bytes of binary data, and converts them into five printable
ASCII characters. The encoding only uses 85 "safe" ASCII
characters, hence its name.

    ----------------------------------------------------

This payload has been encoded with Adobe-flavoured ASCII85.
All subsequent layers are ASCII85 encoded just like this
one, but they require additional processing in order to be
solved.

Decode the payload below to proceed!
  
## Layer 1: Bitwise Operations
Computers are big calculators. They perform operations with
numbers -- adding, subtracting, multiplying, etc. They
represent numbers using binary digits (ones and zeros)
called "bits". For example, here are the decimal numbers
zero to ten with their binary representations:

                    Decimal | Binary
                    --------+---------
                       0    |     0
                       1    |     1
                       2    |    10
                       3    |    11
                       4    |   100
                       5    |   101
                       6    |   110
                       7    |   111
                       8    |  1000
                       9    |  1001
                      10    |  1010

In addition to mathematical operations, computers can
perform operations that act upon the individual bits of a
number. These are called bitwise operations, and there are
only about six different ones: AND, OR, XOR, NOT,
LEFT-SHIFT, and RIGHT-SHIFT.

Bitwise operations are useful when working with binary data
at a low level, such as writing device drivers,
cryptographic algorithms, or working with binary file
formats (as opposed to text formats like XML or JSON).

As an example, let's say we have the decimal numbers 10 and
6, each stored in one byte. A byte contains exactly 8 bits,
so the binary representation is padded out with zeros on the
left. If we ask the computer to perform a bitwise AND
operation on these two bytes, it would do this:

                00001010  <-- decimal 10
            AND 00000110  <-- decimal 6
                --------
                00000010  <-- result: decimal 2

Bitwise AND looks at each bit in both of the bytes. If both
bits are 1, then the resulting bit is 1, otherwise the
resulting bit is 0.

Bitwise operations are not really mathematical operations.
Notice how "10 AND 6 = 2" doesn't make much sense
mathematically. That is because bitwise operations work at
the level of individual bits, ignoring of whatever decimal
number the bits represent.

    ----------------------------------------------------

Like all the layers, the payload is again encoded with
Adobe-flavoured ASCII85. After ASCII85 decoding the payload,
apply the following operations to each byte:

  1. Flip every second bit
  2. Rotate the bits one position to the right

For example:

                        |      Binary      Decimal  Hex
  ----------------------+-------------------------------
  Starting value        | 1 0 1 1 0 1 0 0    180     B4
                        |   v   v   v   v
  Flip every second bit | 1 1 1 0 0 0 0 1    225     E1
                        |  \ \ \ \ \ \ \ \
  Rotate to the right   | 1 1 1 1 0 0 0 0 )  240     F0
                        |  \_____________/

Here are some hints:

 - Bits can be flipped easily using XOR.

 - You can extract specific bits into a separate value using
   AND. This is called "masking".

 - You can use OR to combine some of the bits from one value
   with some of the bits from another value. Just make sure
   that the unimportant bits are masked (all set to zero).
   For example, if you want the first 4 bits of a byte
   combined with the last 4 bits of another byte:
   10100000 OR 00001010 = 10101010

 - Bit shift operations discard bits on one side, and add
   zeros to the other side. If you want to retain the bits
   that will be shifted off the end of a byte, you probably
   need to mask it into a separate variable before doing the
   shift.

## Layer 2: Parity Bit 
Parity bits are used to detect when data is being corrupted
-- for example, by a faulty cable. If the receiver of the
data notices that a parity bit is not correct, that
indicates that the data is being changed somehow.

    ----------------------------------------------------

For each byte of the payload, the seven most significant
bits carry data, and the least significant bit is the parity
bit. Combine the seven data bits from each byte where the
parity bit is correct, discarding bytes where the parity bit
is incorrect.

To determine if the parity bit is correct, first count how
many '1' bits exist within the seven data bits. If the count
is odd, the parity bit should be '1'. If the count is even,
the parity bit should be '0'.

For example, here is the byte 0xA3 (163 in decimal):

  1 0 1 0 0 0 1 1 <-- Parity bit (least significant bit)
  ^ ^ ^ ^ ^ ^ ^
  | | | | | | |
    Data bits

Of the data bits above, three of them are '1's. This is an
odd number, so the '1' parity bit is correct.

To make this layer a little bit easier, the byte size of the
payload is guaranteed to be a multiple of eight. Every group
of eight bytes contains 64 bits total, including 8 parity
bits. Removing the 8 parity bits leaves behind 56 data
bits, which is exactly 7 bytes.

## Layer 3: XOR Encryption 
Exclusive Or (XOR) is another bitwise operation. It's often
used in cryptography to combine two sources of binary data
-- for example, to combine binary data with a secret key,
resulting in scrambled output data.

What makes XOR useful, compared to other bitwise operations
such as AND or OR, is that it can be reversed without losing
any information. If you know the output and one of the
inputs, you can determine what the other input was. It
enables encryption algorithms to be undone, so that data can
be decrypted back to its original state.

For example, let's say we have two input bytes, A and B, and
the result of XOR'ing these two bytes together is another
byte C:

    A XOR B == C

If we have bytes C and B, we're able to determine what A was
by XOR'ing together C and B:

    C XOR B == A

Likewise, if we have bytes C and A, XOR'ing them together
will produce B:

    C XOR A == B

Using XOR by itself to encrypt data is very, very insecure,
as you're about to discover. Good encryption algorithms
still use XOR at certain points, but they have many steps
with various different data transformations.

    ----------------------------------------------------

The payload has been encrypted by XOR'ing each byte with a
secret, cycling key. The key is 32 bytes of random data,
which I'm not going to give you. You will need to use your
hacker skills to discover what the key is, in order to
decrypt the payload.

For example, if it were a three byte secret key:

    Key = 0xAA 0xBB 0xCC

And the original data was seven bytes long:

    Original = 0x11 0x22 0x33 0x44 0x55 0x66 0x77

Then the key would be repeated (cycled) to match the length
of the payload, and then each byte from the key and the
payload would be XOR'd together to create the encrypted
payload.

     Original    Cycled Key    Encrypted
    -------------------------------------
       0x11   XOR   0xAA    ==    0xBB
       0x22   XOR   0xBB    ==    0x99
       0x33   XOR   0xCC    ==    0xFF
       0x44   XOR   0xAA    ==    0xEE
       0x55   XOR   0xBB    ==    0xEE
       0x66   XOR   0xCC    ==    0xAA
       0x77   XOR   0xAA    ==    0xDD

## Layer 4: Network Traffic
When computers send data over a network like the internet,
the data is broken up and placed within packets. As well as
containing the data being sent, packets contain extra data
like the destination address (where the packet should be
sent to), and the source address (where the packet came
from). This extra information allows the packets to be
relayed between many different routers -- travelling across
land, air, ocean, and maybe even outer space -- all
cooperating to send the packet to its intended destination.

If you're familiar with the ancient system of dead tree
communication known as the postal service, packets are a
similar concept to envelopes. A letter (data) is placed
inside an envelope (packet). The destination address is
written on the envelope, probably accompanied by a return
address and a stamp. The people and machines that make up
the postal system use the information on the envelope to
relay it to the correct destination (some of the time). The
receiver then removes the envelope to read the letter
within.

The structure of the data in a packet depends on which
protocol is being used. Protocols are specifications that
define exactly how senders should format packet data before
it is sent over the network, and exactly how receivers
should interpret the data that has come from the network. At
the moment, the networking protocol that most computers use
is TCP/IP, which is a combination of Transmission Control
Protocol (TCP) and Internet Protocol Version 4 (IPv4).

    ----------------------------------------------------

The payload for this layer is encoded as a stream of raw
network data, as if the solution was being received over the
internet. The data is a series of IPv4 packets with User
Datagram Protocol (UDP) inside. Extract the payload data
from inside each packet, and combine them together to form
the solution.

Each packet has three segments: the IPv4 header, the UDP
header, and the data section. So the first 20 bytes of the
payload will be the IPv4 header of the first packet. The
next 8 bytes will be the UDP header of the first packet.
This is followed by a variable-length data section for the
first packet. After the data section you will find the
second packet, starting with another 20 byte IPv4 header,
and so on.

You will need to read the specifications for IPv4 and UDP in
order to parse the data. The official specification for IPv4
is RFC 791 (https://tools.ietf.org/html/rfc791) and for UDP
it is RFC 768 (https://tools.ietf.org/html/rfc768). The
Wikipedia pages for these two protocols are also good, and
probably easier to read than the RFCs.

However, the payload contains extra packets that are not
part of the solution. Discard these corrupted and irrelevant
packets when forming the solution.

Each valid packet of the solution has the following
properties. Discard packets that do not have all of these
properties.

 - The packet was sent FROM any port of 10.1.1.10
 - The packet was sent TO port 42069 of 10.1.1.200
 - The IPv4 header checksum is correct
 - The UDP header checksum is correct

WARNING: Failing to do this properly WILL cause the next
layer to be unsolveable. If you include incorrect packets in
your solution, the result may be readable and look correct,
but its payload WILL be corrupted in ways that are
impossible to detect. Trust me.

The packets appear in the correct order. No reordering is
necessary.

## Layer 5/6: Advanced Encryption Standard
The Advanced Encryption Standard (AES) is an
industry-standard encryption algorithm. In 2001, after a
five year evaluation of 15 different encryption algorithms,
this algorithm was selected as the standard for use by the
U.S. Federal Government. In 2003, the National Security
Agency announced that AES was sufficient to protect the highest 
level of classified information: TOP SECRET. Since
then it has seen wide adoption.

Currently, there are no known attacks capable of breaking
AES encryption when implemented properly. It is generally
considered to be one of the strongest and safest encryption
algorithms.

    ----------------------------------------------------

This payload has been encrypted with AES-256 in Counter Mode
(CTR). To decrypt the payload you will need the encryption
key and the initialization vector (IV). It is not possible
to guess these, so I will just give them to you. They are at
the start of the payload.

But... surprise! The key is also encrypted with AES. It
turns out that the U.S. Government also has standards for
how to encrypt encryption keys. I've encrypted the key using
the AES Key Wrap algorithm specified in RFC 3394. How do you
decrypt the key? Well, you will need another key, called the
"key encrypting key" (KEK), and another initialization
vector. These are also impossible to guess, so I will just
give them to you. They are also at the start of the payload.

But... surprise! Just kidding. I haven't encrypted the KEK.
The U.S. Government does not have a standard for encrypting
key encrypting keys, as far as I'm aware. That would be a
bit too crazy.

The payload is structured like this:

- First 32 bytes: The 256-bit key encrypting key (KEK).
- Next 8 bytes: The 64-bit initialization vector (IV) for
  the wrapped key.
- Next 40 bytes: The wrapped (encrypted) key. When
  decrypted, this will become the 256-bit encryption key.
- Next 16 bytes: The 128-bit initialization vector (IV) for
  the encrypted payload.
- All remaining bytes: The encrypted payload.

The first step is to use the KEK and the 64-bit IV to unwrap
the wrapped key. The second step is to use the unwrapped key
and the 128-bit IV to decrypt the rest of the payload.

Don't try to write the decryption algorithms yourself. Or
do. I'm not your dad. You do you. Personally, I used OpenSSL
to generate the payload for this layer, and reused the
`aes_key_wrap` Ruby gem that I wrote years ago.
