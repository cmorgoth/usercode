CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

OS_NAME:=$(shell uname -s | tr A-Z a-z)
ifeq ($(OS_NAME),darwin)
STDINCDIR := -I/opt/local/include
STDLIBDIR := -L/opt/local/lib
else
STDINCDIR := 
STDLIBDIR := 
endif

CPPFLAGS := $(shell root-config --cflags) $(STDINCDIR)
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR)

CPPFLAGS += -g

#TARGET = DM_ANA

TARGET = DM_ANA_Test

SRC = main.cc DM_StackPlots.cc DM_RatioPlots.cc DM_1DRatio.cc DM_2DRatio.cc DM_Base.cc DM_DY_HTBins.cc DM_TTJets.cc DM_Data.cc DM_ZJetsNuNu.cc DM_WJetsHTBins.cc DM_2D_MR_RSQ_Dist.cc DM_T2CC.cc DM_METPlots.cc

#SRC = main.cc DM_StackPlots.cc DM_RatioPlots.cc DM_1DRatio.cc DM_2DRatio.cc DM_Base.cc DM_TTJets.cc DM_Data.cc DM_DYJetsLL.cc DM_ZJetsNuNu.cc DM_WJetsHTBins_EleTauVeto.cc DM_2D_MR_RSQ_Dist.cc DM_T2CC.cc DM_METPlots.cc

OBJ = $(SRC:.cc=.o)

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc	
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@	
	@echo $<
clean :
	rm -f *.o $(TARGET) *~

