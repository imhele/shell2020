#ifndef __HLIB_PARSER_TYPING_BUFFER
#define __HLIB_PARSER_TYPING_BUFFER

#include "../../utils/helpers/calloc.h"

struct ParserTypingBuffer
{
  int *head;
  int *cursor;
  unsigned int size;
};

void ParserTypingBufferCalloc(struct ParserTypingBuffer **buffer_ref, unsigned int extra_size)
{
  struct ParserTypingBuffer *buffer = *buffer_ref;
  if (buffer == NULL)
    buffer = *buffer_ref = HLIB_CALLOC(struct ParserTypingBuffer);
  if (buffer->cursor - buffer->head + extra_size >= buffer->size)
  {
    int next_size = buffer->size + (extra_size < 32 ? 32 : extra_size);
    int *next_head = HLIB_CALLOC_N(int, next_size);
    if (buffer->size)
    {
      memcpy(next_head, buffer->head, buffer->size * sizeof(int));
      free(buffer->head);
    }
    buffer->cursor = buffer->cursor - buffer->head + next_head;
    buffer->size = next_size;
    buffer->head = next_head;
  }
}

void ParserTypingBufferPush(struct ParserTypingBuffer **buffer_ref, int *value, unsigned int size)
{
  ParserTypingBufferCalloc(buffer_ref, size);
  memcpy((*buffer_ref)->cursor, value, size * sizeof(int));
  (*buffer_ref)->cursor += size;
}

void ParserTypingBufferPushOne(struct ParserTypingBuffer **buffer_ref, int value)
{
  ParserTypingBufferPush(buffer_ref, &value, 1);
}

void ParserTypingBufferUnshift(struct ParserTypingBuffer **buffer_ref, int *value, unsigned int size)
{
  struct ParserTypingBuffer *buffer = *buffer_ref;
  if (buffer == NULL)
    buffer = *buffer_ref = HLIB_CALLOC(struct ParserTypingBuffer);
  int next_size = (buffer->cursor - buffer->head + size >= buffer->size)
                      ? buffer->size + (size < 32 ? 32 : size)
                      : buffer->size;
  int *next_head = HLIB_CALLOC_N(int, next_size);
  memcpy(next_head, value, size * sizeof(int));
  if (buffer->size)
  {
    memcpy(next_head + size, buffer->head, buffer->size * sizeof(int));
    free(buffer->head);
  }
  buffer->cursor = buffer->cursor - buffer->head + next_head + size;
  buffer->size = next_size;
  buffer->head = next_head;
}

void ParserTypingBufferUnshiftOne(struct ParserTypingBuffer **buffer_ref, int value)
{
  ParserTypingBufferUnshift(buffer_ref, &value, 1);
}

#endif /* __HLIB_PARSER_TYPING_BUFFER */
