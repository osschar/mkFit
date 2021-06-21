#ifndef MkStdSeqs_h
#define MkStdSeqs_h

#include "Hit.h"
#include "Track.h"

namespace mkfit {

class Event;
class EventOfHits;

class IterationConfig;

namespace StdSeq
{
    void LoadHits(Event &ev, EventOfHits &eoh);

    void Cmssw_LoadHits_Begin(EventOfHits &eoh, const std::vector<const HitVec*> &orig_hitvectors);
    void Cmssw_LoadHits_End(EventOfHits &eoh);

    // Not used anymore. Left here if we want to experiment again with
    // COPY_SORTED_HITS in class LayerOfHits.
    void Cmssw_Map_TrackHitIndices(const EventOfHits &eoh, TrackVec &seeds);
    void Cmssw_ReMap_TrackHitIndices(const EventOfHits &eoh, TrackVec &out_tracks);

    int  clean_cms_seedtracks_iter(TrackVec *seed_ptr, const IterationConfig& itrcfg,
            const EventOfHits *eohp=nullptr, const MCHitInfoVec* simhitinfop=nullptr);
    
    void find_duplicates(TrackVec &tracks);
    void remove_duplicates(TrackVec &tracks);
    void handle_duplicates(Event *m_event);
      
    void quality_filter(TrackVec &tracks, const int nMinHits);
    void find_duplicates_sharedhits(TrackVec &tracks, const float fraction);

    template<class TRACK>
    bool qfilter_n_hits(const TRACK &t, int nMinHits)
    {
        int seedHits = t.getNSeedHits();
        int seedReduction = (seedHits <= 5) ? 2 : 3;
        return t.nFoundHits() - seedReduction >= nMinHits;
    }

    void find_and_remove_duplicates(TrackVec &tracks, const IterationConfig &itconf);

} // namespace StdSeq

}

#endif
