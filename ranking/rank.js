var http = require("http");
var { Octokit } = require("@octokit/core");
var fs = require("fs");
var token = fs.readFileSync("token.txt").toString();
var data = JSON.parse(fs.readFileSync("data.json"))
const octokit = new Octokit({
    auth: token
})

function updateGist(){
    octokit.request('PATCH /gists/70b1049e28ae65411c6dd10da94016ec', {
        gist_id: '70b1049e28ae65411c6dd10da94016ec',
        description: 'update',
        files: {
          'mcpp.json': {
            content: JSON.stringify(data)
          }
        }
    })
}
function update(dt){
    data[dt.name] = dt.data;
}
var server = http.createServer((req,res)=>{
    req.on("data",(data)=>{
        update(JSON.parse(data.toString()))
        updateGist()
        fs.writeFileSync("data.json",data.toString())
    })
})
server.listen(8080);