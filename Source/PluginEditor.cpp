#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginAudioProcessorEditor::PluginAudioProcessorEditor (PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    gainKnob.setRange(0.0, 1.0, 0.01);
    gainKnob.setValue(0.5);
    addAndMakeVisible(gainKnob);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainKnob, false);
    addAndMakeVisible(gainLabel);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.treeState, "gain", gainKnob);

    delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    delaySlider.setRange(0.0, 1.0, 0.01);
    delaySlider.setValue(0.5);
    addAndMakeVisible(delaySlider);
    delayLabel.setText("Delay", juce::dontSendNotification);
    delayLabel.attachToComponent(&delaySlider, false);
    addAndMakeVisible(delayLabel);
    delaySlider.onValueChange = [this] {
        audioProcessor.setDelay(delaySlider.getValue());  
    };

    
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    feedbackSlider.setRange(0.0, 1.0, 0.01);
    feedbackSlider.setValue(0.5);
    addAndMakeVisible(feedbackSlider);
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    addAndMakeVisible(feedbackLabel);
    feedbackSlider.onValueChange = [this] {
        audioProcessor.setFeedback(feedbackSlider.getValue());  
    };

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);  
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
}

//==============================================================================
void PluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gainKnob.setBounds(100, 100, 100, 100);
    delaySlider.setBounds(250, 100, 100, 100);
    feedbackSlider.setBounds(400, 100, 100, 100);
}
