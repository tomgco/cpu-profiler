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
      , 'id'
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
    var now = Date.now()
    profiler.startProfiling('test');
    setTimeout(function () {
      test = profiler.stopProfiling('test');
      test.title.should.equal('test');
      test.samplesCount.should.be.type('number');
      test.uid.should.be.above(0);
      test.startTime.should.be.above(now);
      test.endTime.should.be.above(now);
      next();
    }, 100);
  });

  it('should not getSample correctly as recording sampling is off by default'
    , function () {
      (function () {
        var sample = test.getSample(0);
        should.not.exist(sample)
      }).should.throw('No sampels have been collected');
    }
  );

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

  it('should have a getSample method for the top root', function () {
    should.exist(test.getSample);
    test.getSample.should.be.type('function');
  });

  it('should getSample correctly', function () {
    var sample = test.getSample(1);
    sample.should.be.type('object')
    validateNode(sample)

    var sample2 = test.getSample(0);
    sample2.should.be.type('object')
    validateNode(sample2)
  });

  it('should not sigfault if you request a sample out of range', function () {
    ;(function () {
      var sample3 = test.getSample(-1);
      should.not.exist(sample3);
    }).should.throw('Index is not in range of samplesCount')

    ;(function () {
      var sample4 = test.getSample(test.samplesCount);
      should.not.exist(sample4);
    }).should.throw('Index is not in range of samplesCount')
  });
});
