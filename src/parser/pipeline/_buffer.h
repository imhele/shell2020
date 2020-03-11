#ifndef __HLIB_PARSER_TYPING_BUFFER
#define __HLIB_PARSER_TYPING_BUFFER

#include "../../utils/helpers/calloc.h"

struct ParserTypingBuffer
{
  char *head;
  char *tail;
  unsigned int size;
};

void ParserTypingBufferCalloc(struct ParserTypingBuffer *buffer, unsigned int extra_size)
{
  if (buffer->tail - buffer->head + extra_size < buffer->size)
    return;

  unsigned int next_size = buffer->size + (extra_size < 32 ? 32 : extra_size);
  char *next_head = HLIB_CALLOC_N(char, next_size);

  if (buffer->size)
  {
    memcpy(next_head, buffer->head, buffer->size * sizeof(char));
    free(buffer->head);
  }

  buffer->tail = buffer->tail - buffer->head + next_head;
  buffer->size = next_size;
  buffer->head = next_head;
}

void ParserTypingBufferPush(struct ParserTypingBuffer *buffer, char *value, unsigned int size)
{
  ParserTypingBufferCalloc(buffer, size);
  if (!size)
    return;
  memcpy(buffer->tail, value, size * sizeof(char));
  buffer->tail += size;
}

void ParserTypingBufferPushOne(struct ParserTypingBuffer *buffer, char value)
{
  ParserTypingBufferPush(buffer, &value, 1);
}

void ParserTypingBufferUnshift(struct ParserTypingBuffer *buffer, char *value, unsigned int size)
{
  if (!size)
    return;

  unsigned int next_size = (buffer->tail - buffer->head + size >= buffer->size)
                               ? buffer->size + (size < 32 ? 32 : size)
                               : buffer->size;
  char *next_head = HLIB_CALLOC_N(char, next_size);
  memcpy(next_head, value, size * sizeof(char));

  if (buffer->size)
  {
    memcpy(next_head + size, buffer->head, (buffer->tail - buffer->head) * sizeof(char));
    free(buffer->head);
  }

  buffer->tail = buffer->tail - buffer->head + next_head + size;
  buffer->size = next_size;
  buffer->head = next_head;
}

void ParserTypingBufferUnshiftOne(struct ParserTypingBuffer *buffer, char value)
{
  ParserTypingBufferUnshift(buffer, &value, 1);
}

unsigned int ParserTypingGetLastUnicodeSize(struct ParserTypingBuffer *buffer)
{
  if (!buffer->size || buffer->tail - buffer->head <= 0)
    return 0;

  if (!((unsigned char)*(buffer->tail - 1) & 0x80))
    return 1;

  unsigned int size = 1;
  unsigned char *tail = (unsigned char *)buffer->tail - 1;
  while (--tail - (unsigned char *)buffer->head >= 0 && (*tail & 0x80) && ++size < 8)
    if ((*tail & 0x40) && (*tail & (1 << (8 - size))))
      return size;

  return 1;
}

unsigned int ParserTypingGetFirstUnicodeSize(struct ParserTypingBuffer *buffer)
{
  if (!buffer->size)
    return 0;

  unsigned int size = 1;
  unsigned char head = *(unsigned char *)buffer->head;
  for (; size < 8 && size < buffer->size; size++)
    if (!((unsigned char)buffer->head[size - 1] & 0x80))
      return 1;
    else if (!(head & (1 << (7 - size))))
      return size;

  return size;
}

#endif /* __HLIB_PARSER_TYPING_BUFFER */
