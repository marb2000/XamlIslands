// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;

using Microsoft.ReactNative;
using Microsoft.ReactNative.CSharp;

namespace SampleLibraryCS
{
    public sealed class Package : IPackage
    {
        public IReadOnlyList<IViewManager> GetViewManagers() => PackageHelpers.GetAllViewManagers();
    }
}
