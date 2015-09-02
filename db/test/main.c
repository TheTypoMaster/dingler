#include <string>
#include <iostream>

#include "base/logging.h"
#include "base/files/file_path.h"
#include "db/db.h"
#include "db/status.h"
#include "db/context.h"
#include "db/transaction.h"
#include "db/mutator.h"
#include "db/table.h"

using std::cout;

int main() {
 db::Context* ctx;
 db::Table* t;
 base::FilePath path(L".");

 auto status = db::Open(path, "index.db", &ctx);
 if (status != db::Status::Ok)
  return -1;

 auto tr = ctx->CreateTransaction(true);

 tr.Begin();

 db::Mutator mut(ctx);
 status = mut.CreateTable("whatever", db::Schema(), &t);
 if (status != db::Status::Ok) {
  tr.Rollback();
  ctx->Close();
  return -1;
 }

 tr.Commit();

 ctx->Close();

 return 0;
}