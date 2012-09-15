/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "meta.pb-c.h"
void   package__init
                     (Package         *message)
{
  static Package init_value = PACKAGE__INIT;
  *message = init_value;
}
size_t package__get_packed_size
                     (const Package *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &package__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t package__pack
                     (const Package *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &package__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t package__pack_to_buffer
                     (const Package *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &package__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Package *
       package__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Package *)
     protobuf_c_message_unpack (&package__descriptor,
                                allocator, len, data);
}
void   package__free_unpacked
                     (Package *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &package__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor package__field_descriptors[13] =
{
  {
    "virtualPath",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Package, virtualpath),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "num",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Package, has_num),
    PROTOBUF_C_OFFSETOF(Package, num),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "realFullPath",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Package, realfullpath),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "isDir",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BOOL,
    PROTOBUF_C_OFFSETOF(Package, has_isdir),
    PROTOBUF_C_OFFSETOF(Package, isdir),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "listItem",
    5,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    PROTOBUF_C_OFFSETOF(Package, n_listitem),
    PROTOBUF_C_OFFSETOF(Package, listitem),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "openMode",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Package, has_openmode),
    PROTOBUF_C_OFFSETOF(Package, openmode),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "mode",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Package, has_mode),
    PROTOBUF_C_OFFSETOF(Package, mode),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Operation",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Package, has_operation),
    PROTOBUF_C_OFFSETOF(Package, operation),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "replicaNo",
    9,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Package, has_replicano),
    PROTOBUF_C_OFFSETOF(Package, replicano),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "opcode",
    10,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Package, opcode),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "rcode",
    11,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Package, rcode),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "migrateInst",
    12,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    PROTOBUF_C_OFFSETOF(Package, has_migrateinst),
    PROTOBUF_C_OFFSETOF(Package, migrateinst),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "targetZHT",
    13,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    PROTOBUF_C_OFFSETOF(Package, has_targetzht),
    PROTOBUF_C_OFFSETOF(Package, targetzht),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned package__field_indices_by_name[] = {
  7,   /* field[7] = Operation */
  3,   /* field[3] = isDir */
  4,   /* field[4] = listItem */
  11,   /* field[11] = migrateInst */
  6,   /* field[6] = mode */
  1,   /* field[1] = num */
  9,   /* field[9] = opcode */
  5,   /* field[5] = openMode */
  10,   /* field[10] = rcode */
  2,   /* field[2] = realFullPath */
  8,   /* field[8] = replicaNo */
  12,   /* field[12] = targetZHT */
  0,   /* field[0] = virtualPath */
};
static const ProtobufCIntRange package__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 13 }
};
const ProtobufCMessageDescriptor package__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "Package",
  "Package",
  "Package",
  "",
  sizeof(Package),
  13,
  package__field_descriptors,
  package__field_indices_by_name,
  1,  package__number_ranges,
  (ProtobufCMessageInit) package__init,
  NULL,NULL,NULL    /* reserved[123] */
};
