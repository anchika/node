#include "node.h"
#include "node_natives.h"
#include "v8.h"
#include "env.h"
#include "env-inl.h"

#include <string.h>
#if !defined(_MSC_VER)
#include <strings.h>
#endif

namespace node {

using v8::HandleScope;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;

Local<String> MainSource(Environment* env) {
  return String::NewFromUtf8(
      env->isolate(), reinterpret_cast<const char*>(node_native),
      NewStringType::kNormal, sizeof(node_native)).ToLocalChecked();
}

void DefineJavaScript(Environment* env, Local<Object> target) {
  HandleScope scope(env->isolate());

  for (int i = 0; natives[i].name; i++) {
    if (natives[i].source != node_native) {
      Local<String> name = String::NewFromUtf8(env->isolate(), natives[i].name);
      Local<String> source =
          String::NewFromUtf8(
              env->isolate(), reinterpret_cast<const char*>(natives[i].source),
              NewStringType::kNormal, natives[i].source_len).ToLocalChecked();
      target->Set(name, source);
    }
  }
}

}  // namespace node
