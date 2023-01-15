## Note from Allen:
I think the challenge can use a bit more than what it is doing right now. During my playthrough, after realizing that K1 ^ K2 == 0xFF and that foo is basically xor, I could theoretically come to a conclusion
that the first call to foo (`foo(inp[i], iv_b[i], K5, K6)`) HAS to be clearing the memory, and attempt to do so, which is the final answer. Thus skipping the need to even look at `gen_keys` function. One way I think
this challenge can be improved is add two constant string, where K7^K8 == 0xFF (to throw the user off), and change gen_keys like so:

```
def gen_keys():
	k = b"\x00"*MAGIC
	keys = []
	for i in range(MAGIC-1):
	    key = random.randbytes(MAGIC)
	    keys.append(key)
	    k = xor(k, xor(key,flag))
	keys.append(xor(xor(xor(k,flag),K7),K8))
	return keys
```

This way the output will be encrypted, and the user would have to go through gen_keys step in order to figure out what's wrong. This will still force the user to figure out the random_bits fiasco since inappropriate input
will still result in jumbled data. the `guardian` function is unnecessary imo.

Or, another change could be using the magic 73:

```
def gen_keys():
	k = b"\x00"*MAGIC
	keys = []
	for i in range(MAGIC-1):
	    key = random.randbytes(MAGIC)
	    keys.append(key)
	    k = xor(k, xor(key,flag))
	keys.append(xor(xor(k,flag), MAGIC))
	return keys
```
