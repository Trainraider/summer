# <span style="color:#fa2; font-family: 'Cursive'; font-size: 1.5em;">Summer</span>

<span style="color:#fff; font-family: 'Palatino'; font-size: 1.2em;">
This is a toy project that uses basic multithreading with posix threads to add
the numbers between 1 and a number provided on the command line. I think it's
useful for others to reference if they are learning to write multithreaded
programs, and for me to reference when I start forgetting details. By default the
thread count will be determined based on how many threads are available
according to the cpu affinity of this process, but if the option `-t` is
supplied, you can specify how many threads you want to run. The automatic
getting of the thread count seems to be Linux only and not portable. It would
need to be implemented seperately for each OS if portability is desired.

If you try a number above about 6 billion it will start overflowing and producing
garbage answers.
</span>

## <span style="color:#fa2; font-family: 'Cursive'; font-size:1.1em;">Usage:</span>
    summer [-t nthreads] num
    summer --help` for more info.


## <span style="color:#fa2; font-family: 'Cursive'; font-size: 1.1em;">Example Usage:</span>

    $ summer -t 12 1000000000
    > Sum: 500000000500000000

    $ summer 4096
    > Sum: 8390656

    $ echo "time -f \"Elapsed Time: %es\" summer -t 1 1000000000" | dash
    > Sum: 500000000500000000
    > Elapsed Time: 0.26s
    
    $ echo "time -f \"Elapsed Time: %es\" summer -t 12 1000000000" | dash
    > Sum: 500000000500000000
    > Elapsed Time: 0.06s

## <span style="color:#fa2; font-family: 'Cursive'; font-size: 1.1em;">Building and Installation:</span>
<span style="color:#fff; font-family: 'Palatino'; font-size: 1.2em;">
(I don't know why you would want to install this to be honest)  
This project actually uses the meson build system, but I use a makefile to
script and shorten calls to meson.</span>

### <span style="color:#fa2; font-family: 'Cursive'; font-size: 1.1em;">Build only:</span>
    make

### <span style="color:#fa2; font-family: 'Cursive'; font-size: 1.1em;">Build and Install:</span>
    make install

