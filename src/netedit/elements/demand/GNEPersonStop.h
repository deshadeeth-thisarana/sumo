/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2021 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    GNEPersonStop.h
/// @author  Pablo Alvarez Lopez
/// @date    Jun 2020
///
// Representation of person stops in NETEDIT
/****************************************************************************/
#pragma once
#include <config.h>
#include <utils/vehicle/SUMOVehicleParameter.h>

#include "GNEDemandElement.h"

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNEPersonStop
 */
class GNEPersonStop : public GNEDemandElement, public SUMOVehicleParameter::Stop {

public:
    /// @brief constructor used for stops over busStops
    GNEPersonStop(GNENet* net, GNEDemandElement* personParent, GNEAdditional* stoppingPlace, const SUMOVehicleParameter::Stop& stopParameter);

    /// @brief constructor used for stops over lanes
    GNEPersonStop(GNENet* net, GNEDemandElement* personParent, GNEEdge* edge, const SUMOVehicleParameter::Stop& stopParameter);

    /// @brief destructor
    ~GNEPersonStop();

    /**@brief get move operation for the given shapeOffset
     * @note returned GNEMoveOperation can be nullptr
     */
    GNEMoveOperation* getMoveOperation(const double shapeOffset);

    /**@brief get begin time of demand element
     * @note: used by demand elements of type "Vehicle", and it has to be implemented as children
     * @throw invalid argument if demand element doesn't has a begin time
     */
    std::string getBegin() const;

    /**@brief writte demand element element into a xml file
     * @param[in] device device in which write parameters of demand element element
     */
    void writeDemandElement(OutputDevice& device) const;

    /// @brief check if current demand element is valid to be writed into XML (by default true, can be reimplemented in children)
    bool isDemandElementValid() const;

    /// @brief return a string with the current demand element problem (by default empty, can be reimplemented in children)
    std::string getDemandElementProblem() const;

    /// @brief fix demand element problem (by default throw an exception, has to be reimplemented in children)
    void fixDemandElementProblem();

    /// @name members and functions relative to elements common to all demand elements
    /// @{
    /// @brief obtain VClass related with this demand element
    SUMOVehicleClass getVClass() const;

    /// @brief get color
    const RGBColor& getColor() const;

    /// @}

    /// @name Functions related with geometry of element
    /// @{
    /// @brief update pre-computed geometry information
    void updateGeometry();

    /// @brief Returns position of demand element in view
    Position getPositionInView() const;
    /// @}

    /// @name inherited from GUIGlObject
    /// @{
    /**@brief Returns the name of the parent object
     * @return This object's parent id
     */
    std::string getParentName() const;

    /**@brief Returns the boundary to which the view shall be centered in order to show the object
     * @return The boundary the object is within
     */
    Boundary getCenteringBoundary() const;

    /// @brief split geometry
    void splitEdgeGeometry(const double splitPosition, const GNENetworkElement* originalElement, const GNENetworkElement* newElement, GNEUndoList* undoList);

    /**@brief Draws the object
     * @param[in] s The settings for the current view (may influence drawing)
     * @see GUIGlObject::drawGL
     */
    void drawGL(const GUIVisualizationSettings& s) const;

    /// @}

    /// @name inherited from GNEPathManager::PathElement
    /// @{

    /// @brief compute pathElement
    void computePathElement();

    /**@brief Draws partial object
     * @param[in] s The settings for the current view (may influence drawing)
     * @param[in] lane lane in which draw partial
     * @param[in] segment PathManager segment (used for segment options)
     * @param[in] offsetFront extra front offset (used for drawing partial gl above other elements)
     */
    void drawPartialGL(const GUIVisualizationSettings& s, const GNELane* lane, const GNEPathManager::Segment* segment, const double offsetFront) const;

    /**@brief Draws partial object (junction)
     * @param[in] s The settings for the current view (may influence drawing)
     * @param[in] fromLane from GNELane
     * @param[in] toLane to GNELane
     * @param[in] segment PathManager segment (used for segment options)
     * @param[in] offsetFront extra front offset (used for drawing partial gl above other elements)
     */
    void drawPartialGL(const GUIVisualizationSettings& s, const GNELane* fromLane, const GNELane* toLane, const GNEPathManager::Segment* segment, const double offsetFront) const;

    /// @brief get first path lane
    GNELane* getFirstPathLane() const;

    /// @brief get last path lane
    GNELane* getLastPathLane() const;
    /// @}

    /// @brief inherited from GNEAttributeCarrier
    /// @{
    /* @brief method for getting the Attribute of an XML key
     * @param[in] key The attribute key
     * @return string with the value associated to key
     */
    std::string getAttribute(SumoXMLAttr key) const;

    /* @brief method for getting the Attribute of an XML key in double format (to avoid unnecessary parse<double>(...) for certain attributes)
     * @param[in] key The attribute key
     * @return double with the value associated to key
     */
    double getAttributeDouble(SumoXMLAttr key) const;

    /* @brief method for getting the Attribute of an XML key in Position format (used in person plans)
     * @param[in] key The attribute key
     * @return double with the value associated to key
     */
    Position getAttributePosition(SumoXMLAttr key) const;

    /* @brief method for setting the attribute and letting the object perform demand element changes
     * @param[in] key The attribute key
     * @param[in] value The new value
     * @param[in] undoList The undoList on which to register changes
     * @param[in] net optionally the GNENet to inform about gui updates
     */
    void setAttribute(SumoXMLAttr key, const std::string& value, GNEUndoList* undoList);

    /* @brief method for setting the attribute and letting the object perform demand element changes
     * @param[in] key The attribute key
     * @param[in] value The new value
     * @param[in] undoList The undoList on which to register changes
     */
    bool isValid(SumoXMLAttr key, const std::string& value);

    /* @brief method for enable attribute
     * @param[in] key The attribute key
     * @param[in] undoList The undoList on which to register changes
     * @note certain attributes can be only enabled, and can produce the disabling of other attributes
     */
    void enableAttribute(SumoXMLAttr key, GNEUndoList* undoList);

    /* @brief method for disable attribute
     * @param[in] key The attribute key
     * @param[in] undoList The undoList on which to register changes
     * @note certain attributes can be only enabled, and can produce the disabling of other attributes
     */
    void disableAttribute(SumoXMLAttr key, GNEUndoList* undoList);

    /* @brief method for check if the value for certain attribute is set
     * @param[in] key The attribute key
     */
    bool isAttributeEnabled(SumoXMLAttr key) const;

    /// @brief get PopPup ID (Used in AC Hierarchy)
    std::string getPopUpID() const;

    /// @brief get Hierarchy Name (Used in AC Hierarchy)
    std::string getHierarchyName() const;
    /// @}

    /// @brief get parameters map
    const std::map<std::string, std::string>& getACParametersMap() const;

protected:
    /// @brief get first valid lane
    const GNELane* getFirstAllowedLane() const;

    /// @brief draw personStop over lane
    void drawPersonStopOverLane(const GUIVisualizationSettings& s, const double exaggeration, const RGBColor& stopColor) const;

    /// @brief draw personStop over busStop
    void drawPersonStopOverBusStop(const GUIVisualizationSettings& s, const double exaggeration, const RGBColor& stopColor) const;

private:
    /// @brief method for setting the attribute and nothing else
    void setAttribute(SumoXMLAttr key, const std::string& value);

    /// @brief method for enabling the attribute and nothing else (used in GNEChange_EnableAttribute)
    void setEnabledAttribute(const int enabledAttributes);

    /// @brief set move shape
    void setMoveShape(const GNEMoveResult& moveResult);

    /// @brief commit move shape
    void commitMoveShape(const GNEMoveResult& moveResult, GNEUndoList* undoList);

    /// @brief Invalidated copy constructor.
    GNEPersonStop(const GNEPersonStop&) = delete;

    /// @brief Invalidated assignment operator
    GNEPersonStop& operator=(const GNEPersonStop&) = delete;
};
