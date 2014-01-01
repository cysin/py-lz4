import lz4
data = '11111111abb'
compressed = lz4.compress(data)
decompressed = lz4.decompress(compressed)
print decompressed
