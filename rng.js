
class rng{
    seed;
    mnum;
    constructor(sed){
        this.seed = sed;
        this.mnum = sed;
        if(this.seed<1000){
            this.seed = (sed*1000)+sed;
            this.mnum = this.seed;
        }
    };
    getSeed(){
        return this.seed;
    }
    r(to){
        //console.log(this.mnum);
        this.mnum = this.mnum*(this.mnum+this.seed);//xxxxaaaaxxxx
        //console.log(this.mnum);
        this.mnum = (((this.mnum%10000000000)-(this.mnum%100000)))/100000;
        return (this.mnum%to);
    }
};
var r = new rng(199);
for(var i = 0;i<20;i++){
    console.log(r.r(10));
}