from flask import Flask, jsonify
import request
app = Flask(__name__)
@app.route('/')		## defined decorator
def home():			## binds '/' with home()
	return "<h1>hello</h1>"

@app.route('/json')
def json():
	return jsonify({'fn':'rishabh', 'ln':'malik'})

@app.route('/store', methods=['POST'])
def post_method():
	request_data=request.get_json()
	new_store={'name':request_data['fn'],'item':[]}
	st
	return jsonify({'fn':'rishabh', 'ln':'malik'})	

if(__name__=='__main__'):
	app.run(port=5000)

