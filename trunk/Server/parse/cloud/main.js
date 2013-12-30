//ENTRY POINT

Parse.Cloud.define('submitScore',
    function(req, res) {
        var score = req.params.score;
		res.success(score + "1000");
});