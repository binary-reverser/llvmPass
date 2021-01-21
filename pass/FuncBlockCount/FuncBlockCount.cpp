#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

namespace {
	struct FuncBlockCount : public FunctionPass {
		static char ID;
		FuncBlockCount():FunctionPass(ID) {}

		void countBlockInLoop(Loop *L, unsigned nest) {
			unsigned numBlocks = 0;
			Loop::block_iterator blkIter;
			for(blkIter=L->block_begin();blkIter!=L->block_end();++blkIter){
				numBlocks++;
			}
			errs()<<"Loop level"<<nest<<" has "<<numBlocks<<" blocks\n";
			std::vector<Loop*> subLoops = L->getSubLoops();
			Loop::iterator j, f;
			for(j=subLoops.begin(),f=subLoops.end();j!=f;++j)
				countBlockInLoop(*j, nest+1);
			
		}

		bool runOnFunction(Function &F) override {
			errs()<<"Function: "<<F.getName()<<'\n';
			LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
			auto Loops = LI.getLoopsInPreorder();
			for(Loop *L:Loops)
				countBlockInLoop(L, 0);
			return false;
		}

		virtual void getAnalysisUsage(AnalysisUsage& AU) const override {
			AU.addRequired<LoopInfoWrapperPass>();
		}
	};
}

char FuncBlockCount::ID = 0;
static RegisterPass<FuncBlockCount> X("funcblockcount", "Function Block Count", false, false);
