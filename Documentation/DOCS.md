#Function Docs

See demo.c for a demo of these functions.

## struct ByteStream
* buffer - raw byte stream buffer
* actualsize - logical size of contents in buffer
* bufsize - total size of the buffer
* resizeBuff - resizing function called when the buffer needs to grow, the user can replace this function with one of their own design.

## int defaultResizeStream(struct ByteStream \*stream)
Resizes the buffer using Knuth's Buddy algorithm (i.e. double the size of the buffer)

## int initByteStreamWithSize(struct ByteStream \*stream, long size)
Initializes the byte stream with the size. The function sets the resizeBuff to defaultResizeStream.

## int initByteStream(struct ByteStream \*stream)
Initializes the byte stream with the default size. The default size is 1024 bytes.


## writeToByteStream( struct ByteStream \*stream, object)
This macro writes object to the stream, resizing the buffer if needed. The object must be some local data object (e.g. int, double, struct). Pointers and arrays aren't supported by this function.

## void writeStreamToFile(FILE \*f, struct ByteStream \*stream)
Writes the entire stream to f. f is assumed to be writable.

