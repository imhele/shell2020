#ifndef __HLIB_PARSER_TYPING_BUFFER
#define __HLIB_PARSER_TYPING_BUFFER

#include "../../utils/helpers/calloc.h"

struct ParserTypingBuffer
{
  int *head;
  int *tail;
  unsigned int size;
};

void ParserTypingBufferCalloc(struct ParserTypingBuffer *buffer, unsigned int extra_size)
{
  if (buffer->tail - buffer->head + extra_size < buffer->size)
    return;

  int next_size = buffer->size + (extra_size < 32 ? 32 : extra_size);
  int *next_head = HLIB_CALLOC_N(int, next_size);

  if (buffer->size)
  {
    memcpy(next_head, buffer->head, buffer->size * sizeof(int));
    free(buffer->head);
  }

  buffer->tail = buffer->tail - buffer->head + next_head;
  buffer->size = next_size;
  buffer->head = next_head;
}

void ParserTypingBufferPush(struct ParserTypingBuffer *buffer, int *value, unsigned int size)
{
  ParserTypingBufferCalloc(buffer, size);
  if (!size)
    return;
  memcpy(buffer->tail, value, size * sizeof(int));
  buffer->tail += size;
}

void ParserTypingBufferPushOne(struct ParserTypingBuffer *buffer, int value)
{
  ParserTypingBufferPush(buffer, &value, 1);
}

void ParserTypingBufferUnshift(struct ParserTypingBuffer *buffer, int *value, unsigned int size)
{
  if (!size)
    return;

  int next_size = (buffer->tail - buffer->head + size >= buffer->size)
                      ? buffer->size + (size < 32 ? 32 : size)
                      : buffer->size;
  int *next_head = HLIB_CALLOC_N(int, next_size);
  memcpy(next_head, value, size * sizeof(int));

  if (buffer->size)
  {
    memcpy(next_head + size, buffer->head, buffer->size * sizeof(int));
    free(buffer->head);
  }

  buffer->tail = buffer->tail - buffer->head + next_head + size;
  buffer->size = next_size;
  buffer->head = next_head;
}

void ParserTypingBufferUnshiftOne(struct ParserTypingBuffer *buffer, int value)
{
  ParserTypingBufferUnshift(buffer, &value, 1);
}

#endif /* __HLIB_PARSER_TYPING_BUFFER */
