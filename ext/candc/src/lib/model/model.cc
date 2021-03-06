// C&C NLP tools
// Copyright (c) Universities of Edinburgh, Oxford and Sydney
// Copyright (c) James R. Curran
//
// This software is covered by a non-commercial use licence.
// See LICENCE.txt for the full text of the licence.
//
// If LICENCE.txt is not included in this distribution
// please email candc@it.usyd.edu.au to obtain a copy.

#include "base.h"

#include "config/config.h"

#include "model/model.h"

using namespace std;

namespace NLP { namespace Model {

Info::Info(void)
  : Cfg("info", "model statistics", HIDE_HELP | HIDE_CONFIG),
    nklasses(*this, "nclasses", "the number of tags in the tagset"),
    nevents(*this, "nevents", "the number of instances in the training data"),
    ncontexts(*this, "ncontexts", "the number of unique instances in the training data"),
    nfeatures(*this, "nfeatures", "the number of features in the model"),
    nattributes(*this, "nattributes", "the number of attributes in the model"){}

Info::Info(const std::string &filename)
  : Cfg("info", "model statistics", HIDE_HELP | HIDE_CONFIG),
    nklasses(*this, "nclasses", "the number of tags in the tagset"),
    nevents(*this, "nevents", "the number of instances in the training data"),
    ncontexts(*this, "ncontexts", "the number of unique instances in the training data"),
    nfeatures(*this, "nfeatures", "the number of features in the model"),
    nattributes(*this, "nattributes", "the number of attributes in the model"){
  ifstream in(filename.c_str());
  if(!in)
    throw NLP::IOException("could not open model information file for reading", filename);

  load(in, filename);
}

Model::Model(const std::string &name, const OpPath &path, double SIGMA, ulong NITER,
	     Flags flags, ushort order)
  : Cfg("model", "maximum entropy model", SPACE | flags, order),
    path(path),
    comment(*this, "comment", "an explanatory comment for the model"),
    data(*this, "data", "the path to the original training data file"),
    solver(*this, "solver", "the maximum entropy model solver [gis, bfgs]", "gis"),
    update(*this, "smoothing", "the smoothing method [none, gaussian]", "gaussian"),
    sigma(*this, "sigma", "the smoothing parameter", SIGMA),
    niterations(*this, "niterations", "the number of interations the solver should perform", NITER),
    weights(*this, "weights", "the weights file path", "//weights", &path){}

void
Model::check(void){
  Cfg::check();
  if(solver() != "gis" && solver() != "bfgs")
    throw ConfigError("the solver option must be one of [gis, bfgs]", solver.NAME);
  if(update() != "none" && update() != "gaussian")
    throw ConfigError("the smoothing option must be one of [none, gaussian]", update.NAME);
}

Config::Config(const std::string &name, const std::string &desc,
	       const OpPath *base, Mode mode, double SIGMA, ulong NITER)
  : Directory(name, desc, base, mode == TRAIN ? SHOW_ALL | IGNORE_MISSING : SHOW_ALL),
    model(name, path, SIGMA, NITER, mode == DECODE ? (HIDE_HELP | HIDE_CONFIG) : SHOW_ALL){
  reg(model);
}

} }
