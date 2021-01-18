# Neon District - Function Core Solution
Credit to *mk* for solving the challenge.

Write-up by *PolarityInversion* 2021/01/17

Puzzle images: [PNG](https://pbs.twimg.com/media/Dzqs4BjUcAAcx_a?format=jpg&name=small) [SVG](https://neon-district-easter-egg.s3.amazonaws.com/w3Lc0Me_tO-7h3.FuNc710nc0rE-GlHf.svg)

## Puzzle Background
The Function Core puzzle is the final puzzle of the Neon District crypto-puzzle series. After solving preceding puzzles of increasing difficulty, one eventually reaches The Function Core, which encodes the private key to an Ethereum wallet containing 30 Ether (15 ETH initially and another 15 ETH added a year later). 

The puzzle is an image depicting 16 concentric rings, with each ring being comprised of distinct segments differentiated by their colour, line thickness, and the angular rotation of each ring relative to other rings.
## Solution
The private key is encoded into the colour and thickness of 64 arc segments, which together form 16 concentric rings made up of 4 arc segments each. There are 4 unique colours in each segment and 4 unique thickness values, encoding 2-bits of information in each property for a total of 4-bits of information per segment. Each concentric ring appears to be rotated by 1/16th of a circle (22.5 deg) relative to the immediately adjacent ring. This hints at the required operations to solve the puzzle.

The solution requires the mapping of each unique colour and thickness to a value in the range of 0-3 and the concatenation of these values across all segments in the ring (with the thickness and colour values interleaved from segment to segment). Each ring then comprises 4 segments of 4 bits of information each for a total of 16 bits of information per ring. Across 16 rings (each with 16 bits of information) this formulation provides for the total 256 bits required to form a private key.

After composing the bits in each individual ring, each set of bits for each ring must be circularly shifted to the right (that is, any bit shifted past the least significant bit position must be moved to the most significant bit). The puzzle subtly hints at this operation with its circular shape and increasing angular rotation of each ring as you move from one ring to the next. The exact number of bits to shift is also hinted at by the circular rotation of each ring, which is visually depicted as a 1/16th rotation per each ring level.

Finally, after composing the bits of the individual rings in this fashion, the last manipulation step for each ring level is to subtract from its post-circularly shifted value, the pre-circularly shifted value of the preceding inner ring. The resulting bits of each post-subtraction operation must then be concatenated starting from the innermost ring moving outwards in sequence, which forms the unadulterated private key and solution to the puzzle. This final step was alluded to in a hint from the author wherein the function call f_i(x_i, y_(i-1)) was shown above the updated image (see PNG link).

## Discussion
The initial premise of the puzzle is quite clever, with subtle hints embedded within the puzzle itself to indicate the correct solution method. With exclusion of the final manipuation step, if one were to deduce the solution method from these hints, then it would lead to a relatively small search space of around 300k combinations to determine the important parameters, such as colour values, stroke width values, ring reading order, segment reading order, and bit ordering of stroke/colour bits. It is notable that one hint provided by the author mentioned the puzzle was solvable using either the PNG or the SVG images. While technically true, this was a red herring of sorts, as the solution is much simpler using the SVG file, which reveals the order that the segments and rings should be interpreted.

In general, this was a fun puzzle to dissect and I’m excited that it was finally solved. However, a word of criticism should be directed to the rather arbitrary final manipulation step, which casts a cloud over an otherwise brilliant puzzle. An infinite number of mathematical operations could have been applied at this step, and without some breadcrumb or hint to narrow the options, the puzzle was unsolvable until the hint was released a year later. Creators of puzzles must take great care that in their efforts to achieve increased difficulty they do not rely on increased obscurity. Would-be solvers who worked on the puzzle in the initial year of its release could have no sooner solved it than they could have brute forced a Bitcoin private key.

According to the author, the final manipulation step was added last-minute due to an unexpected increase to the prize pool. While not based on any evidence, the cynic in me is skeptical the puzzle was not intentionally released in an unsolvable form to facilitate dragging out the expected influx of attention to their for-profit venture. /conspiracytheroy