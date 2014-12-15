-- get the most massive z=0 haloes
select * from MPAHaloTrees..MR where redshift between 0 and 0.01 and np between 100000 and 1000000000 order by np DESC

-- find the progenitor tree of halo with haloid=x
select PROG.* from 
  MPAHaloTrees..MR PROG,
  MPAHaloTrees..MR DES
 where DES.TreeRootId = 140005829017979
   and PROG.haloId between DES.haloId and DES.lastprogenitorId

-- get the galaxies associated with this treeId
select *
  from MPAGalaxies..DeLucia2006a
 where treeId=140005829000000

select * --or those to match the lightcone
  from Guo2010a..MR a,
  MPAHaloTrees..MR b
 where b.HaloId=a.HaloId
   and b.TreeRootId=436017494000000

--or get galaxies in this tree in which lightcone
select a.HaloId,b.HaloId,b.TreeRootId, c.* from 
  Guo2010a..MR a,
  MPAHaloTrees..MR b,
  Henriques2012a.wmap1.M05_001 c
 where b.HaloId=a.HaloId
   and a.GalaxyId=c.GalId
   and b.TreeRootId=229002732000000


-- get the lightcone associated with the position of this cluster 
select a.*,b.HaloId, b.TreeRootId, c.* from 
  Guo2010a..MR a,
  MPAHaloTrees..MR b,
  Henriques2012a.wmap1.M05_009 c
 where b.HaloId=a.HaloId
   and a.GalaxyId=c.GalId
   and c.ra between 0.25 and 0.5
   and c.dec between -0.3 and 0.05

-- get the 1.4by1.4 sq. deg. lightcone with corresponding stellar masses
select a.centralMvir,a.GalaxyId,b.HaloId, b.TreeRootId, c.i1,c.i2,c.SDSS_i,c.z_app,c.ra,c.dec,c.GalID, a.stellarMass from 
  Guo2010a..MR a,
  MPAHaloTrees..MR b,
  Henriques2012a.wmap1.M05_001 c
 where b.HaloId=a.HaloId
   and a.GalaxyId=c.GalId
