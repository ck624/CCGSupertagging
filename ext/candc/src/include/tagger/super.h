/* -*- Mode: C++; -*- */
// C&C NLP tools
// Copyright (c) Universities of Edinburgh, Oxford and Sydney
// Copyright (c) James R. Curran
//
// This software is covered by a non-commercial use licence.
// See LICENCE.txt for the full text of the licence.
//
// If LICENCE.txt is not included in this distribution
// please email candc@it.usyd.edu.au to obtain a copy.

namespace NLP {
  namespace Tagger {

    class Super: public Tagger {
    public:
      class Config: public Tagger::Config {
      public:
	Op<ulong> category_cutoff;
	OpPath postags;
	OpPath posdict;

      	Config(const OpPath *base = 0, Mode mode = DECODE,
	       const std::string &name = "super",
	       const std::string &desc = "super tagger config");
      };
    public:
      Super(Super::Config &config);
      Super(Super &other);

      virtual ~Super(void);

      // the set of POS tags the super tagger uses as features
      TagSet postags(void) const;
      // posdict stores the set of supertags permissible for a given POS tag
      TagSetDict posdict(void) const;
    protected:
      // private implementation trick
      class Impl;
    };

  }
}
