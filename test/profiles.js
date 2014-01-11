var should = require('should');
var profiler = require('../');

describe('profiles', function () {
  var test;

  function validateNode (node) {
    var numbers = [
      'childrenCount'
      , 'callUid'
      , 'lineNumber'
      , 'hitCount'
    ];
    numbers.forEach(function (num) {
      node[num].should.be.type('number');
    });
    node.scriptName.should.be.type('string');
    node.functionName.should.be.type('string');
    node.bailoutReason.should.be.type('string')

    if (Array.isArray(node.children)) {
      node.children.forEach(validateNode);
    }
  }

  it('should export profiling methods', function () {
    should.exist(profiler.startProfiling);
    profiler.startProfiling.should.be.type('function');

    should.exist(profiler.startProfiling);
    profiler.stopProfiling.should.be.type('function');
  });

  it('create a profile result', function (next) {
    profiler.startProfiling('test');
    setTimeout(function () {
      test = profiler.stopProfiling('test');
      test.title.should.equal('test');
      test.samplesCount.should.be.type('number');
      test.uid.should.be.above(0);
      next();
    }, 100);
  });

  it('should contain delete method', function () {
    should.exist(test.delete);
    test.delete.should.be.type('function');
  });

  it('should contain top root', function () {
    should.exist(test.topRoot);
  });

  it('should have correct root contents', function () {
    ['topRoot'].forEach(function (type) {
      validateNode(test[type]);
    });
  });

  it('should have a getChild method for the top root', function () {
    ['topRoot'].forEach(function (type) {
      should.exist(test[type].getChild);
      test[type].getChild.should.be.type('function');
    });
  });

  it('should getChild correctly', function () {
    ['topRoot'].forEach(function (type) {
      var child = test[type].getChild(0);
      validateNode(child);
    });
  });

  it('should getTopDownRoot correctly', function () {
    ['getTopDownRoot'].forEach(function (call) {
      var tree = test[call]();
      validateNode(tree);
    });
  });

  it('create a profile result with samples', function (next) {
    profiler.startProfiling('test', true);
    setTimeout(function () {
      test = profiler.stopProfiling('test');
      test.title.should.equal('test');
      test.samplesCount.should.be.type('number');
      test.uid.should.be.above(0);
      test.samplesCount.should.be.above(0);
      next();
    }, 100);
  });
});
