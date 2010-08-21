
/**
 * @file Central place for How To Write Pneumatic
 * 
 * Coding conventions, design decisions, etc.
 */

/* 

-------------------------------------------------------------------------------
 Design decisions
-------------------------------------------------------------------------------

* Fast incremental compilation is king
 - No precompiled headers (maybe a very slim one when stable)
 - Generally keep API definitions separate to implementation code
 - Pimpl idiom might come in handy etc etc

* Performance matters




-------------------------------------------------------------------------------
 Coding Conventions
-------------------------------------------------------------------------------

Anything that warranted a few moments thought should be recorded here as canon. 
There must be a document out there that forms a good basis...

* Documentation
Loosely Doxygen, but lets not bother actually using Doxygen until its stable.

* Comments
When on same line as code, should start at column #60
Conversational commments (questions, todos, thoughts) formatted: // MTJ:21/08/10

* Width
All dividers and comments should be 80 characters long. Usually also code,
but exceptions are tolerable.

* Line endings: 
Windows

* Macros and defines:
All start PN_ to avoid conflicts














*/