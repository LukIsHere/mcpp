drawCircle(x,y,r,block){
    var ax = x;
    var ay = y;
    var ar = r;
    for(var i = 0;i<ar;i++){
      var sqrtemp = Math.round(Math.sqrt(ar*ar-i*i))
      this.mirrorP(ax,i,ay,sqrtemp,block);
      this.mirrorP(ay,sqrtemp,ax,i,block);
      for(var j = 0;j<sqrtemp;j++){
        this.mirrorP(ax,i,ay,sqrtemp-j,block);
        this.mirrorP(ay,sqrtemp-j,ax,i,block);
      }
    }
    this.setblock(ax,ay,block)
  }
  mirrorP(x,xm,y,ym,block){
    this.setblock(x+xm,y+ym,block)
    this.setblock(x+xm,y-ym,block)
    this.setblock(x-xm,y+ym,block)
    this.setblock(x-xm,y-ym,block)
  }
//js concept off drawing circle tehniq
//soon will be re write in C++
